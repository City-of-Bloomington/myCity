<?php
/**
 * @copyright 2022 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE
 */
declare (strict_types=1);
namespace Web\Controllers;

use Web\Services\MasterAddressGateway;
use Web\Controller;
use Web\View;
use Web\Views\HelpView;

class HelpController extends Controller
{
    public function __invoke(array $params): View
    {
        return new HelpView();
    }
}
