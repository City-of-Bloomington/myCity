include make.conf
# Variables from make.conf:
#
# DOCKER_REPO
SHELL := /bin/bash
APPNAME := mycity

REQS := git sassc msgfmt docker
K := $(foreach r, ${REQS}, $(if $(shell command -v ${r} 2> /dev/null), '', $(error "${r} not installed")))

LANGUAGES := $(wildcard language/*/LC_MESSAGES)
JAVASCRIPT := $(shell find public -name '*.js' ! -name '*-*.js')
THEMES := $(shell ls -d data/Themes/*/)
VERSION := $(shell cat VERSION | tr -d "[:space:]")
COMMIT := $(shell git rev-parse --short HEAD)

default: clean compile test package

clean:
	rm -Rf build/${APPNAME}*
	for f in $(shell find public/css   -name '*-*.css'   ); do rm $$f; done
	for f in $(shell find data/Themes  -name '*-*.css'   ); do rm $$f; done

compile:
	cd ${LANGUAGES} && msgfmt -cv *.po
	cd public/css                 && sassc -t compact -m screen.scss screen-${VERSION}.css;
	for d in ${THEMES}; do sassc -t compact -m $${d}public/css/screen.scss $${d}public/css/screen-${VERSION}.css; done;
	for f in ${JAVASCRIPT}; do cp $$f $${f%.js}-${VERSION}.js; done

test:
	vendor/phpunit/phpunit/phpunit -c src/Test/Unit.xml

package:
	[[ -d build ]] || mkdir build
	rsync -rl --exclude-from=buildignore . build/${APPNAME}
	cd build && tar czf ${APPNAME}-${VERSION}.tar.gz ${APPNAME}

docker: package
	docker build ./build/${APPNAME} -t ${DOCKER_REPO}/${APPNAME}:${VERSION}-${COMMIT}
	docker push ${DOCKER_REPO}/${APPNAME}:${VERSION}-${COMMIT}

$(LANGUAGES):
	cd $@ && msgfmt -cv *.po
