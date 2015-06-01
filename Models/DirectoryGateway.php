<?php
/**
 * @copyright 2015 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
namespace Application\Models;

class DirectoryGateway
{
    public static $phoneNumberFields = [
        'office', 'fax', 'cell', 'other', 'pager'
    ];

    public static function info($username)
    {
        $url = DIRECTORY_SERVER.'/people/view?format=json;username='.$username;
        return WebService::loadJsonResponse($url);
    }
}