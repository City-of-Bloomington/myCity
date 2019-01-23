<?php
/**
 * @copyright 2015-2019 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE
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
        'RESIDENTIAL PARKING ZONE'  => 'parkingZone',
        'REDEVELOPMENT ZONE'        => 'redevelopmentZone'
    ];
    private static function createPurposeVariables(&$json)
    {
        if (  !empty($json['purposes'])) {
            foreach ($json['purposes'] as $p) {
                if (array_key_exists($p['purpose_type'], self::$purposeMap)) {
                    $f = self::$purposeMap[$p['purpose_type']];
                    $json[$f][] = $p['name'];
                }
            }
        }
    }

    public static function search($query)
    {
        $url = MASTER_ADDRESS.'?format=json;address='.urlencode($_GET['address']);
        return WebService::loadJsonResponse($url);
    }

    public static function info(int $address_id)
    {
        $url  = MASTER_ADDRESS."/addresses/$address_id?format=json";
        $json = WebService::loadJsonResponse($url);
        self::createPurposeVariables($json);
        return $json;
    }
}
