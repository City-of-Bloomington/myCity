SHELL := /bin/bash
APPNAME := myCity

REQS := git sassc msgfmt
K := $(foreach r, ${REQS}, $(if $(shell command -v ${r} 2> /dev/null), '', $(error "${r} not installed")))

LANGUAGES := $(wildcard language/*/LC_MESSAGES)
JAVASCRIPT := $(shell find public -name '*.js' ! -name '*-*.js')

VERSION := $(shell cat VERSION | tr -d "[:space:]")
#COMMIT := $(shell git rev-parse --short HEAD)

default: clean compile test package

clean:
	rm -Rf build/${APPNAME}*
	cd public/css && rm -f *.css*

compile: $(LANGUAGES)
	cd public/css && sassc -t compact -m screen.scss screen-${VERSION}.css
	for f in ${JAVASCRIPT}; do cp $$f $${f%.js}-${VERSION}.js; done

test:
	vendor/phpunit/phpunit/phpunit -c src/Test/Unit.xml

package:
	[[ -d build ]] || mkdir build
	rsync -rl --exclude-from=buildignore . build/${APPNAME}
	cd build && tar czf ${APPNAME}-${VERSION}.tar.gz ${APPNAME}

$(LANGUAGES):
	cd $@ && msgfmt -cv *.po
