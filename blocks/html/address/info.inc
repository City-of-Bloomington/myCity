<?php
/**
 * @copyright 2015 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param int $_GET['address_id']
 */
use Application\Models\MasterAddressGateway;
use Application\Models\CityCouncilGateway;

$address = MasterAddressGateway::info($_GET['address_id']);
foreach (MasterAddressGateway::$purposeMap as $p) {
    $l  = $p.'s';
    $$l = '';

    if (!empty($address[$p])) {
        $$l = "<tr><th>{$this->_([$p, $l, 2])}</th><td><ul>";
        foreach ($address[$p] as $value) {
            $$l.= "<li>$value</li>";
        }
        $$l.= "</ul></td></tr>";
    }
}

$districtMember = '';
$atLargeMembers = '';
if (!empty($address['councilDistrict'])) {
    $districtName = $address['councilDistrict'][0];
    $district = CityCouncilGateway::members($districtName);
    $atLarge  = CityCouncilGateway::members(CityCouncilGateway::AT_LARGE);
    $districtMember = "<tr><th>$districtName</th><td>{$district[0]['name']}</td></tr>";
    $atLargeMembers = "<tr><th>{$this->_('atLarge')}</th><td><ul>";
        foreach ($atLarge as $member) {
            $atLargeMembers.= "<li>$member[name]</li>";
        }
    $atLargeMembers.= "</ul></td></tr>";
}

echo "
<h1>{$address['streetAddress']}</h1>
<section>
    <h2>{$this->_(['service', 'services', 2])}</h2>
    <table>
        <tr><th>{$this->_('trashDay')}</th>
            <td>{$address['trashDay']}</td>
        </tr>
        <tr><th>{$this->_('recycleWeek')}</th>
            <td>{$address['recycleWeek']}</td>
        </tr>
        $neighborhoodAssociations
        $historicDistricts
        $economicDevelopmentAreas
    </table>
</section>

<section>
    <h2>{$this->_('government')}</h2>
    <table>
        <tr><th>{$this->_('jurisdiction')}</th>
            <td>{$address['jurisdiction']}</td>
        </tr>
        <tr><th>{$this->_('township')}</th>
            <td>{$address['township']}</td>
        </tr>
        $councilDistricts
    </table>
</section>

<section>
    <h2>{$this->_('votingInfo')}</h2>
    <table>
        $districtMember
        $atLargeMembers
    </table>
</section>

<section>
    <h2>{$this->_('gis')}</h2>
    <table>
        <tr><th>{$this->_('latitude')}/{$this->_('longitude')}</th>
            <td>{$address['latitude']} {$address['longitude']}</td>
        </tr>
        <tr><th>{$this->_('statePlane')} x/y</th>
            <td>{$address['statePlane']['x']} {$address['statePlane']['y']}</td>
        </tr>
    </table>
</section>
";
