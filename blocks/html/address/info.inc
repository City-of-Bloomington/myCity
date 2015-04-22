<?php
/**
 * @copyright 2015 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param stdClass $this->address JSON object with address data
 */
use Application\Models\MasterAddressGateway;

foreach (MasterAddressGateway::$purposeMap as $p) {
    $l  = $p.'s';
    $$l = '';

    if (!empty($this->address[$p])) {
        $$l = "<tr><th>{$this->_([$p, $l, 2])}</th><td><ul>";
        foreach ($this->address[$p] as $value) {
            $$l.= "<li>$value</li>";
        }
        $$l.= "</ul></td></tr>";
    }
}

echo "
<h1>{$this->address['streetAddress']}</h1>
<section>
    <h2>{$this->_(['service', 'services', 2])}</h2>
    <table>
        <tr><th>{$this->_('trashDay')}</th>
            <td>{$this->address['trashDay']}</td>
        </tr>
        <tr><th>{$this->_('recycleWeek')}</th>
            <td>{$this->address['recycleWeek']}</td>
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
            <td>{$this->address['jurisdiction']}</td>
        </tr>
        <tr><th>{$this->_('township')}</th>
            <td>{$this->address['township']}</td>
        </tr>
        $councilDistricts
    </table>
</section>

<section>
    <h2>{$this->_('gis')}</h2>
    <table>
        <tr><th>{$this->_('latitude')}/{$this->_('longitude')}</th>
            <td>{$this->address['latitude']} {$this->address['longitude']}</td>
        </tr>
        <tr><th>{$this->_('statePlane')} x/y</th>
            <td>{$this->address['statePlane']['x']} {$this->address['statePlane']['y']}</td>
        </tr>
    </table>
</section>
";
