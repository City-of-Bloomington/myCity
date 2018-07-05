<?php
/**
 * @copyright 2015-2018 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 */
namespace Application\Models;

use Blossom\Classes\Url;

class CityCouncilGateway
{
    const AT_LARGE   = 'At-Large';

    /**
     * Council district names are named differently in
     * MasterAddress and OnBoard.  This maps between
     * the two names
     */
    public static $councilDistricts = [
        // Master Address name                => OnBoard name
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
        global $CITY_COUNCIL;
        return $CITY_COUNCIL[self::$councilDistricts[$master_address_district]];
    }
}
