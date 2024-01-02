<?php
/**
 * @copyright 2020-2024 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE
 */
declare (strict_types=1);

$ROUTES = new Aura\Router\RouterContainer(BASE_URI);
$map    = $ROUTES->getMap();

$map->tokens(['id' => '\d+']);

$map->get('home.index',    '/'    , Web\Controllers\SearchController::class);
$map->get('home.help',     '/help', Web\Controllers\HelpController::class);
$map->get('address.info',  '/{id}', Web\Controllers\InfoController::class);
