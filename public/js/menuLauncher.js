"use strict";
(function () {
    var launcherClick = function(e)  {
            var openMenus  = document.querySelectorAll('.menuLinks.open'),
                menu = e.target.parentElement.querySelector('.menuLinks'),
                len = openMenus.length,
                i = 0;
            for (i=0; i<len; i++) {
                openMenus[i].classList.remove('open');
                setTimeout(function() { openMenus[i].classList.add('closed'); }, 300);
            }
            menu.classList.remove('closed');
            menu.classList.add('open');
            e.stopPropagation();
        },
        documentClick = function(e) {
            var openMenus   = document.querySelectorAll('.menuLinks.open'),
                len = openMenus.length,
                i = 0;
            for (i=0; i<len; i++) {
                openMenus[i].classList.remove('open');
                setTimeout(function() { openMenus[i].classList.add('closed'); }, 300);
            }
        };

    var launchers = document.querySelectorAll('.menuLauncher'),
        len = launchers.length,
        i = 0;
    for (i=0; i<len; i++) {
        launchers[i].addEventListener('click', launcherClick);
    }
    document.addEventListener('click', documentClick);
})()