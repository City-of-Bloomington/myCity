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
<div class="pageOverview">
    <div class="container">
        <div>
            <p><?= $this->_('pageOverview_address', 'messages'); ?></p>
        </div>
        <aside>
            <dl></dl>
            <dd><?= $this->_('aboutThisAddress'); ?></dd>
            <dd><?= $this->_('governmentLinks'); ?></dd>
            <dd><?= $this->_('votingInfo'); ?></dd>

        </aside>
    </div>
</div>

<section id="aboutThisAddress">
    <h2><?= $this->_('aboutThisAddress') ?></h2>

    <div class="myCity-addressInfo-container">
        <div class="myCity-trash-container">
            <dl class="myCity-addressInfo-keyValuePair myCity-trash-day">
                <dt><?= $this->_('trashDay') ?></dt>
                <dd><?= ucfirst(strtolower($address['trashDay'])) ?></dd>
            </dl>
            <dl class="myCity-addressInfo-keyValuePair myCity-trash-recycleWeek">
                <dt><?= $this->_('nextRecyclePickup') ?></dt>
                <dd>Week <?= $address['recycleWeek'] ?></dd>
            </dl>
            <p class="myCity-trash-details">Trash pick-up dates are according to the regular schedule. Some conditions may cause delays to the schedule. Please see <a href="/trash">Trash & Recycling Pickup</a> for details.</p>
        </div>
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
            <?php
                $purposes = $address->getPurposeValuesByType();

                $purposesToDisplayHere = [
                    'neighborhoodAssociation',
                    'historicDistrict',
                    'economicDevelopmentArea'
                ];
                foreach ($purposesToDisplayHere as $p) {
                    if (!empty($purposes[$p])) {
                        echo "<dl class=\"$p\"><dt>{$this->_($p)}</dt>";
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

    <?php
        if (!empty($purposes['parkingZone'])) {
            echo "
            <div class=\"parking\">
                <div class=\"container\">
            ";
                foreach ($purposes['parkingZone'] as $zone) {
                    $zone = View::escape($zone);
                    echo "
                    <dl><dt>$zone</dt>
                        <dd></dd>
                    </dl>
                    ";
                }
            echo "
                </div>
            </div>
            ";
        }
    ?>

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
    <h1><?= $this->_('governmentLinks'); ?></h1>

    <div>
        <div>
            <dl class="state">
                <dt><?= $this->_('state'); ?></dt>
                <dd><?= $address['state']; ?></dd>
            </dl>
            <dl class="county">
                <dt><?= $this->_('county'); ?></dt>
                <dd><?= $address['county']; ?></dd>
            </dl>
            <dl class="city">
                <dt><?= $this->_('city'); ?></dt>
                <dd><?= $address['city']; ?></dd>
            </dl>
        </div>
    </div>
</section>

<section id="votingInfo">
    <h1><?= $this->_('votingInfo'); ?></h1>

    <div class="mayor">
        <h2><?= $this->_('mayor'); ?></h2>
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
        <h2><?= $this->_('clerk'); ?></h2>
        <?php
            $contactInfo->entry = DirectoryGateway::info('clerk');
            echo $contactInfo->render('html', $this->template);
        ?>
    </div>
</section>
