<?php
/**
 * @copyright 2012-2018 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 */
include '../bootstrap.php';
use Blossom\Classes\Template;

// Create the default Template
$template = !empty($_REQUEST['format'])
	? new Template('default',$_REQUEST['format'])
	: new Template('default');
$controller = new Application\Controllers\IndexController($template);
$controller->index();
echo $template->render();
