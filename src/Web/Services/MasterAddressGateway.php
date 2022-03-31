<?php
/**
 * @copyright 2022 City of Bloomington, Indiana
 * @license https://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE
 */
declare (strict_types=1);
namespace Web\Services;

class MasterAddressGateway extends WebService
{
    public static function search(string $query): ?array
    {
        $params = http_build_query(['format'=>'json', 'address'=>$query], '', ';');
        $url    = MASTER_ADDRESS."/addresses?$params";
        return parent::doJsonRequest($url);
    }

    public static function info(int $address_id): ?array
    {
        $out = [];
        $url = MASTER_ADDRESS."/addresses/$address_id?format=json";
        $res = parent::doJsonRequest($url);
        $loc = self::activeLocation($res);
        if ($loc) {
            if ($loc['address_id'] != $address_id) {
                return self::info($loc['address_id']);
            }

            $out['address' ] = $res['address'];
            $out['location'] = $loc;
            $out['subunits'] = $res['subunits'];
            $out['places'  ] = $res['places'];

            foreach ($res['purposes'] as $p) {
                $out['purposes'][$p['purpose_type']][] = $p['name'];
            }
        }

        return $out;
    }

    private static function activeLocation(array $response): array
    {
        foreach ($response['locations'] as $l) {
            if ($l['active']) { return $l; }
        }
    }
}
