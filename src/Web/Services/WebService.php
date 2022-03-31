<?php
/**
 * @copyright 2022 City of Bloomington, Indiana
 * @license https://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE
 */
declare (strict_types=1);
namespace Web\Services;

class WebService
{
	protected static function get(string $url): ?string
	{
		$request = curl_init($url);
		curl_setopt($request, CURLOPT_RETURNTRANSFER, true);
		curl_setopt($request, CURLOPT_FOLLOWLOCATION, true);
		$res     = curl_exec($request);
		return $res ? $res : null;
	}

	protected static function doJsonRequest(string $url): ?array
	{
        $res = self::get($url);
        if ($res) {
            return json_decode($res, true);
        }
        return null;
	}
}
