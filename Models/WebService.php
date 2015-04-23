<?php
/**
 * @copyright 2015 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
namespace Application\Models;

use Blossom\Classes\Url;

class WebService
{
    public static function loadJsonResponse($url)
    {
        $response = Url::get($url);
        if ($response) {
            $json = json_decode($response, true);
            return $json;
        }
    }
}