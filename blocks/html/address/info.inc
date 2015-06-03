<?php
/**
 * @copyright 2015 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param Address $this->address
 * @param int $_GET['address_id']
 */
use Application\Models\MasterAddressGateway;
use Application\Models\CityCouncilGateway;
use Application\Models\DirectoryGateway;

use Blossom\Classes\Block;
use Blossom\Classes\View;

$address  = $this->address;
?>
<section id="aboutThisAddress">
    <h2><?= $this->_('aboutThisAddress') ?></h2>

    <div class="myCity-addressInfo-container">
        <?php if(isset($address['trashDay'])): ?>
            <div class="myCity-trash-container">
                <dl class="myCity-addressInfo-keyValuePair modTrashDay">
                    <dt><?= $this->_('trashDay') ?></dt>
                    <dd><?= ucfirst(strtolower($address['trashDay'])) ?></dd>
                </dl>
                <dl class="myCity-addressInfo-keyValuePair modRecycleWeek">
                    <dt><?= $this->_('nextRecyclePickup') ?></dt>
                    <dd>Week <?= $address['recycleWeek'] ?></dd>
                </dl>
                <p class="myCity-trash-details">
                <?php
                    echo sprintf($this->_('sanitationDetails', 'messages'), '<a href="/trash">', '</a>');
                ?>
                </p>
            </div>
        <?php endif; ?>
        <?php if(isset($address['latitude']) && isset($address['longitude'])): ?>
            <div class="myCity-location-container">
                <div class="myCity-location-latLon">
                    <dl class="myCity-addressInfo-keyValuePair modLatLon">
                        <dt>Latitude</dt>
                        <dd><?= $address['latitude'] ?></dd>
                    </dl>
                    <dl class="myCity-addressInfo-keyValuePair modLatLon">
                        <dt>Longitude</dt>
                        <dd><?= $address['longitude'] ?></dd>
                    </dl>
                </div>
                <div class="myCity-location-additionalInfo">
                    <?php
                        $purposes = $address->getPurposeValuesByType();

                        $purposesToDisplayHere = [
                            'neighborhoodAssociation',
                            'historicDistrict',
                            'economicDevelopmentArea'
                        ];
                        foreach ($purposesToDisplayHere as $p) {
                            if (!empty($purposes[$p])) {
                                echo "<dl class=\"myCity-addressInfo-keyValuePair modLocation\"><dt>{$this->_($p)}</dt>";
                                foreach ($purposes[$p] as $value) {
                                    $value = View::escape($value);
                                    echo "<dd>$value</dd>";
                                }
                                echo "</dl>";
                            }
                        }
                    ?>

                </div>
            </div>
        <?php endif; ?>
        <?php if (!empty($purposes['parkingZone'])): ?>
            <div class="myCity-parking-container">
                <?php
                    foreach ($purposes['parkingZone'] as $zone) {
                        $zone = ucwords(strtolower(View::escape($zone)));
                        echo "
                            <dl class=\"myCity-parking-details\">
                                <dt>$zone</dt>
                                <dd>Permit required Monday &ndash; Friday, 8:00am &ndash; 5:00pm</dd>
                            </dl>
                        ";
                    }
                ?>
            </div>
        <?php endif; ?>
    </div>

    <div class="location">
        <div class="container">
            <dl class="jurisdiction">
                <dt><?= $this->_('jurisdiction'); ?></dt>
                <dd><?= $address['jurisdiction']; ?></dd>
            </dl>
            <dl class="township">
                <dt><?= $this->_('township'); ?></dt>
                <dd><?= $address['township']; ?></dd>
            </dl>
        </div>
    </div>


    <div class="government">
        <div class="container">
            <dl class="city">
                <dt><?= $this->_('city'); ?></dt>
                <dd><?= $address['city']; ?></dt>
            </dl>
            <dl class="township">
                <dt><?= $this->_('township'); ?></dt>
                <dd><?= $address['township']; ?></dt>
            </dl>
        </div>
    </div>
</section>

<section id="governmentLinks">
    <h2><?= $this->_('governmentLinks'); ?></h2>

    <div>
        <div>
        <?php
            global $GOVERNMENTAL_LINKS;
            foreach (['state', 'county', 'city'] as $region) {
                echo "
                <dl class=\"$region\">
                    <dt>{$this->_($region)}</dt>
                    <dd>{$address[$region]}</dd>
                ";
                    if (array_key_exists($address[$region], $GOVERNMENTAL_LINKS)) {
                        echo '<dd><table>';
                        foreach ($GOVERNMENTAL_LINKS[$address[$region]] as $type=>$link) {
                            $label = $this->_($type);
                            echo "
                            <tr><th>$label:</th>
                                <td><a href=\"$link[url]\">$link[text]</a></td>
                            </tr>
                            ";
                        }
                        echo '</table></dd>';
                    }
                echo "
                </dl>
                ";
            }
        ?>
        </div>
    </div>
</section>

<section id="votingInfo">
    <h2><?= $this->_('votingInfo'); ?></h2>

    <div class="mayor">
        <h3><?= $this->_('mayor'); ?></h3>
        <?php
            $contactInfo = new Block('directory/contactInfo.inc');

            $contactInfo->entry = DirectoryGateway::info('mayor');
            echo $contactInfo->render('html', $this->template);
        ?>
    </div>
    <?php
        $districtMember = '';
        $atLargeMembers = '';
        if (!empty(         $purposes['councilDistrict'])) {
            $districtName = $purposes['councilDistrict'][0];
            $district = CityCouncilGateway::members($districtName);
            $atLarge  = CityCouncilGateway::members(CityCouncilGateway::AT_LARGE);

            $districtName = View::escape($districtName);


            if (count($atLarge)) {
                echo "<div class=\"council\"><h2>{$this->_('atLarge')}</h2>";
                foreach ($atLarge as $member) {
                    if (   !empty($member['email'])
                        && false !== strpos($member['email'], DIRECTORY_DOMAIN)
                        && preg_match('|([a-z]+)@'.DIRECTORY_DOMAIN.'|',$member['email'], $matches)) {

                        $contactInfo->entry = DirectoryGateway::info($matches[1]);
                        echo $contactInfo->render('html', $this->template);
                    }
                }
                echo "</div>";
            }
            if (count($district)) {
                echo "<div class=\"council\"><h2>$districtName</h2>";
                foreach ($district as $member) {
                    if (   !empty($member['email'])
                        && false !== strpos($member['email'], DIRECTORY_DOMAIN)
                        && preg_match('|([a-z]+)@'.DIRECTORY_DOMAIN.'|',$member['email'], $matches)) {

                        $contactInfo->entry = DirectoryGateway::info($matches[1]);
                        echo $contactInfo->render('html', $this->template);
                    }
                }
                echo "</div>";
            }
        }
    ?>
    <div class="clerk">
        <h3><?= $this->_('clerk'); ?></h3>
        <?php
            $contactInfo->entry = DirectoryGateway::info('clerk');
            echo $contactInfo->render('html', $this->template);
        ?>
    </div>
</section>
