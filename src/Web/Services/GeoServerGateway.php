<?php
/**
 * @copyright 2022 City of Bloomington, Indiana
 * @license https://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE
 */
declare (strict_types=1);
namespace Web\Services;

class GeoServerGateway extends WebService
{
    private static $url = GEOSERVER.'/publicgis/ows?service=WFS&version=1.0.0&request=GetFeature&maxFeatures=50&outputFormat=application%2Fjson';

    public static function parks(float $lat, float $long): array
    {
        $json = self::lazyLoad('ParkLocationPoints');
        return self::sortedFeatures($json, $lat, $long);
    }

    public static function schools(float $lat, float $long): array
    {
        $json = self::lazyLoad('Schools');
        return self::sortedFeatures($json, $lat, $long);
    }

    public static function playgrounds(float $lat, float $long): array
    {
        $json = self::lazyLoad('Playgrounds');
        return self::sortedFeatures($json, $lat, $long);
    }

    private static function lazyLoad(string $layerName): array
    {
        $file = SITE_HOME."/$layerName.json";
        if (file_exists($file)) {
            $json = json_decode(file_get_contents($file), true);
        }
        else {
            $url  = self::$url."&typeName=publicgis:$layerName";
            $json = parent::doJsonRequest($url);
            file_put_contents($file, json_encode($json, JSON_PRETTY_PRINT));
        }
        return $json;
    }

    private static function sortedFeatures(array $json, float $lat, float $lon): array
    {
        $out = [];
        foreach ($json['features'] as $f) {
            $p = $f['properties'];
            $p['distance'] = self::distance($lat, $lon, (float)$p['lat'], (float)$p['lon']);
            $out[] = $p;
        }
        usort($out, function($a, $b) { return ($a['distance'] < $b['distance']) ? -1 : 1; });
        return $out;
    }

    private static function distance(float $latitude1, float $longitude1, float $latitude2, float $longitude2): float
    {
        $lat1 = deg2rad($latitude1);
        $lon1 = deg2rad($longitude1);
        $lat2 = deg2rad($latitude2);
        $lon2 = deg2rad($longitude2);

        $dLat = ($lat2 - $lat1) / 2;
        $dLon = ($lon2 - $lon1) / 2;

        $a = sin($dLat) * sin($dLat) + cos($lat1) * cos($lat2) * sin($dLon) * sin($dLon);
        $c = 2 * asin(sqrt($a));
        $d = $c * 3961; // miles

        return $d;
    }
}
