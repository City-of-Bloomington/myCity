<?php
/**
 * @copyright 2015 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
namespace Application\Models;

use Blossom\Classes\Url;

class MasterAddressGateway
{
    public static $purposeMap = [
        'ECONOMIC DEVELOPMENT AREA' => 'economicDevelopmentArea',
        'CITY COUNCIL DISTRICT'     => 'councilDistrict',
        'HISTORIC DISTRICT'         => 'historicDistrict',
        'NEIGHBORHOOD ASSOCIATION'  => 'neighborhoodAssociation',
        'RESIDENTIAL PARKING ZONE'  => 'parkingZone'
    ];
    private static function createPurposeVariables(&$json)
    {
        foreach ($json['purposes'] as $p) {
            if (array_key_exists($p['type'], self::$purposeMap)) {
                $f = self::$purposeMap[$p['type']];
                $json[$f][] = $p['description'];
            }
        }
    }

    private static function loadJsonResponse($url)
    {
        $response = Url::get($url);
        if ($response) {
            $json = json_decode($response, true);
            return $json;
        }
    }

    public static function search($query)
    {
        $url = MASTER_ADDRESS.'?format=json;queryType=address;query='.urlencode($_GET['address']);
        return self::loadJsonResponse($url);
    }

    public static function info($address_id)
    {
        $address_id = (int)$address_id;
        if ($address_id) {
            $url = MASTER_ADDRESS.'/addresses/viewAddress.php?format=json;address_id='.urlencode($address_id);
            $json = self::loadJsonResponse($url);
            self::createPurposeVariables($json);
            return $json;
        }
    }

}