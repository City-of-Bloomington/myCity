<?php
/**
 * @copyright 2022-2024 City of Bloomington, Indiana
 * @license https://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE
 */
declare (strict_types=1);
namespace Web\Info;

use Web\Services\MasterAddressGateway as MA;

class Controller extends \Web\Controller
{
    public function __invoke(array $params): \Web\View
    {
        $res = MA::info((int)$params['id']);

        if ($res) {
            return new View($res);
        }
        return new \Web\Views\NotFoundView();
    }
}
