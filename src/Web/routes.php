<?php
/**
 * @copyright 2020 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE
 */
declare (strict_types=1);

$rf = new \Aura\Router\RouterFactory(BASE_URI);
$ROUTES = $rf->newInstance();
$ROUTES->setTokens(['id' => '\d+']);

$ROUTES->add('home.index',   '/'    )->setValues(['controller' => 'Web\Controllers\SearchController']);
$ROUTES->add('home.help',    '/help')->setValues(['controller' => 'Web\Controllers\HelpController']);
$ROUTES->add('address.info', '/{id}')->setValues(['controller' => 'Web\Controllers\InfoController']);
