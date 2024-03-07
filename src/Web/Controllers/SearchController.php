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
use Web\Views\SearchView;

class SearchController extends Controller
{
    public function __invoke(array $params): View
    {
        if (!empty($_GET['query'])) {
            $res   = MasterAddressGateway::search($_GET['query']);
            #$valid = self::validate($res);

            if ($res) {
                if (count($res) == 1) {
                    header('Location: '.View::generateUrl('address.info', ['id'=>$res[0]['id'] ]));
                    exit();
                }

                return new SearchView($_GET['query'], $res);
            }
            return new SearchView($_GET['query']);
        }
        return new SearchView();
    }

    private static function validate(array $addresses): array
    {
        $valid = [];
        foreach ($addresses as $a) {
            if ($a['active'] && $a['status']=='current') {
                $valid[] = $a;
            }
        }
        return $valid;
    }
}

