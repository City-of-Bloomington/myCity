<?php
/**
 * @copyright 2015-2016 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 */
namespace Application\Models;

use Blossom\Classes\Url;

class CityCouncilGateway
{
    const COUNCIL_ID = 1;
    const AT_LARGE   = 'At-Large';

    private static $json;

    /**
     * Council district names are named differently in
     * MasterAddress and CivicLegislation.  This maps between
     * the two names
     */
    public static $councilDistricts = [
        // Master Address name                => CivicLegislation name
        'BLOOMINGTON CITY COUNCIL DISTRICT 1' => 'District I',
        'BLOOMINGTON CITY COUNCIL DISTRICT 2' => 'District II',
        'BLOOMINGTON CITY COUNCIL DISTRICT 3' => 'District III',
        'BLOOMINGTON CITY COUNCIL DISTRICT 4' => 'District IV',
        'BLOOMINGTON CITY COUNCIL DISTRICT 5' => 'District V',
        'BLOOMINGTON CITY COUNCIL DISTRICT 6' => 'District VI',
        self::AT_LARGE                        => self::AT_LARGE
    ];

    public static function members($master_address_district)
    {
        if (!self::$json) {
            $url = CIVIC_LEGISLATION.'/committees/members?format=json;committee_id='.self::COUNCIL_ID;
            self::$json = WebService::loadJsonResponse($url);
        }
        $members = [];
        foreach (self::$json['seats'] as $seat) {
            if ($seat['name'] === self::$councilDistricts[$master_address_district]) {
                $members[] = $seat['currentMember'];
            }
        }
        return $members;
    }
}
