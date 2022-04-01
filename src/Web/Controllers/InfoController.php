<?php
/**
 * @copyright 2022 City of Bloomington, Indiana
 * @license https://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE
 */
declare (strict_types=1);
namespace Web\Controllers;

use Web\Services\MasterAddressGateway as MA;
use Web\Services\GeoServerGateway     as GEO;
use Web\Controller;
use Web\View;
use Web\Views\InfoView;

class InfoController extends Controller
{
    public function __invoke(array $params): View
    {
        $res = MA::info((int)$params['id']);

        if ($res) {
            $schools     = GEO::schools    ($res['address']['latitude'], $res['address']['longitude']);
            $parks       = GEO::parks      ($res['address']['latitude'], $res['address']['longitude']);
            $playgrounds = GEO::playgrounds($res['address']['latitude'], $res['address']['longitude']);
            return new InfoView($res, $schools, $parks, $playgrounds);
        }
        return new \Web\Views\NotFoundView();
    }
}
