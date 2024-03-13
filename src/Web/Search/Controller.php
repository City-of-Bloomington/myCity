<?php
/**
 * @copyright 2024 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE
 */
declare (strict_types=1);
namespace Web\Search;

use Web\Services\MasterAddressGateway;

class Controller extends \Web\Controller
{
    public function __invoke(array $params): \Web\View
    {
        if (!empty($_GET['query'])) {
            $res   = MasterAddressGateway::search($_GET['query']);

            if ($res) {
                if (count($res) == 1) {
                    header('Location: '.\Web\View::generateUrl('address.info', ['id'=>$res[0]['id'] ]));
                    exit();
                }

                return new View($_GET['query'], $res);
            }
            return new View($_GET['query']);
        }
        return new View();
    }
}

