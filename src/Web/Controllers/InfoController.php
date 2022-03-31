<?php
/**
 * @copyright 2022 City of Bloomington, Indiana
 * @license https://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE
 */
declare (strict_types=1);
namespace Web\Controllers;

use Web\Services\MasterAddressGateway;
use Web\Controller;
use Web\View;
use Web\Views\InfoView;

class InfoController extends Controller
{
    public function __invoke(array $params): View
    {
        $res = MasterAddressGateway::info((int)$params['id']);

        if ($res) {
            return new InfoView($res);
        }
        return new \Web\Views\NotFoundView();
    }
}
