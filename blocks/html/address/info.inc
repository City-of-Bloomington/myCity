<?php
/**
 * @copyright 2015-2016 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @param Address $this->address
 * @param int $_GET['address_id']
 */
use Application\Models\MasterAddressGateway;
use Application\Models\CityCouncilGateway;
use Application\Models\DirectoryGateway;

use Blossom\Classes\Block;

$address  = $this->address;
?>
<section class="uiBlock" id="about-this-address">
    <header class="uiBlock-header">
        <h2 class="uiBlock-title"><?= $this->_('aboutThisAddress') ?></h2>
    </header>
    <div class="uiBlock-content">
        <div class="myCity-addressInfo">
            <?php if(isset($address['latitude']) && isset($address['longitude'])): ?>
                <?php
                    $inOrOut = $address['jurisdiction'] === 'Bloomington'
                        ? 'Inside'
                        : 'Outside';
                ?>
                <div        class="myCity-location-container">
                    <div    class="myCity-location-cityLimits">
                        <dl class="myCity-addressInfo-keyValuePair">
                            <dt>This address is</dt>
                            <dd><?= $inOrOut ?> City Limits</dd>
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
                                        $value = self::escape($value);
                                        echo "<dd>$value</dd>";
                                    }
                                    echo "</dl>";
                                }
                            }
                            if ($address['jurisdiction'] === 'Monroe County') {
                                echo'<p>For more information about this address, see the <a href="http://www.co.monroe.in.us/tsd/gis.aspx">Monroe County GIS website</a>.</p>';
                            }
                        ?>
                        <?php if (!empty($address['township'])): ?>
                            <dl class="myCity-addressInfo-keyValuePair modLocation">
                                <dt><?= $this->_('township') ?></dt>
                                <dd><?= $address['township'] ?></dd>
                            </dl>
                        <?php endif ?>
                    </div>
                </div>
            <?php endif; ?>
            <?php if (isset($address['trashDay'])): ?>
                <div    class="myCity-trash-container">
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
            <?php if (!empty($purposes['parkingZone'])): ?>
                <div class="myCity-parking-container">
                    <?php
                        foreach ($purposes['parkingZone'] as $zone) {
                            $zone = ucwords(strtolower(self::escape($zone)));
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
    </div>
</section>

<section class="uiBlock" id="find-your-government-online">
    <header class="uiBlock-header">
        <h2 class="uiBlock-title"><?= $this->_('governmentLinks'); ?></h2>
    </header>
    <div class="uiBlock-content">
        <div class="myCity-govOnline">
            <?php
                global $GOVERNMENTAL_CONTACT_INFO;
                foreach (['state', 'county', 'jurisdiction'] as $region) {
                    $regionName = $address[$region] === 'IN'
                        ? 'Indiana'
                        : $address[$region];

                    if ($address['jurisdiction'] === 'Bloomington' && $region === 'jurisdiction') {
                        $region = 'city';
                    }
                    echo "
                    <dl><dt>{$this->_($region)}</dt>
                        <dd>$regionName</dd>
                    ";
                    if (array_key_exists($address[$region], $GOVERNMENTAL_CONTACT_INFO)) {
                        echo '<dd><dl>';
                        foreach ($GOVERNMENTAL_CONTACT_INFO[$address[$region]]['online'] as $type=>$link) {
                            $label = ucfirst($this->_($type));
                            echo "
                            <dt>$label:</dt>
                            <dd><a href=\"$link[url]\">$link[text]</a></dd>
                            ";

                        }
                        echo '</dl></dd>';
                        echo '<dd><dl>';
                        foreach ($GOVERNMENTAL_CONTACT_INFO[$address[$region]]['offline'] as $type=>$info) {
                            $label = ucfirst($this->_($type));
                            echo "
                            <dt>$label:</dt>
                            <dd>$info</dd>
                            ";
                        }
                        echo '</dl></dd>';
                    }
                    echo "
                    </dl>
                    ";
                }
            ?>
        </div>
    </div>
</section>

<?php if($address['jurisdiction'] === 'Bloomington'): ?>
    <section class="uiBlock" id="elected-officials">
        <header class="uiBlock-header">
            <h2 class="uiBlock-title"><?= $this->_('votingInfo'); ?></h2>
        </header>
        <div class="uiBlock-content">
            <?php $mayorInfo = DirectoryGateway::info('hamiltoj'); ?>
            <?php if (count($mayorInfo)): ?>
                <div         class="myCity-mayor">
                    <div     class="myCity-mayor-photoContainer">
                        <img class="myCity-mayor-photo" srcset="css/img/mayor-1x.jpg 1x, css/img/mayor-2x.jpg 2x" sizes="437px" src="css/img/mayor-1x.jpg" />
                    </div>
                    <div     class="myCity-mayor-details">
                        <div class="myCity-mayor-title"><?= $this->_('mayor'); ?></div>
                        <h2  class="myCity-mayor-name"><?= $mayorInfo['firstname'] ?> <?= $mayorInfo['lastname'] ?></h2>
                        <table class="table-contact">
                            <tr><th>Email</th>
                                <td><?= $mayorInfo['email'] ?></td>
                            </tr>
                            <tr><th>Mailing Address</th>
                                <td>Office Of The Mayor<br />401 N Morton St<br />Bloomington, IN 47404</td>
                            </tr>
                            <tr><th>Telephone</th>
                                <td><?= $mayorInfo['office'] ?></td>
                            </tr>
                        </table>
                        <div class="myCity-mayor-biography">
                            <h3>About the Mayor</h3>
                            <p>John has worked extensively as a public servant in Democratic government, leading two state agencies, advising a Governor and Lieutenant Governor, and serving as an elected official.  As the Secretary of the Indiana Family and Social Services Administration, he oversaw the implementation of Medicaid and welfare programs, services for the elderly, disabled, mentally ill, and children at risk, and state-wide community development and housing programs – all executed by a staff of 10,000 Hoosiers with an annual budget of $6 billion. Earlier he served as Commissioner of the Indiana Department of Environmental Management, the agency tasked with the statewide protection of Indiana’s air, water and land. John served as an elected member of the Board of Trustees for the Monroe County Community School Corporation. Throughout his time in Bloomington, John has served on many state and local commissions and boards, including chairing the Bloomington Commission on Sustainability and the Shalom Community Center board, as well as national boards such as the National Community Land Trust Network.</p>
                        </div>
                    </div>
                </div>
            <?php else: ?>
                <h1>Error retrieving Mayor info</h1>
            <?php endif ?>
            <?php
                $atLargeContact = new Block('directory/atLargeContact.inc');
                $districtMember = '';
                $atLargeMembers = '';
                if (!empty(         $purposes['councilDistrict'])) {
                    $districtName = $purposes['councilDistrict'][0];
                    $district = CityCouncilGateway::members($districtName);
                    $atLarge  = CityCouncilGateway::members(CityCouncilGateway::AT_LARGE);

                    $districtName = self::escape($districtName);
                    $districtNumber = self::escape(filter_var($districtName, FILTER_SANITIZE_NUMBER_INT));
                }
            ?>
            <?php if (count($atLarge)): ?>
                <div class="myCity-atLarge">
                    <h2 class="myCity-electedOfficials-subheading"><?= $this->_('atLarge'); ?></h2>
                    <?php
                        foreach ($atLarge as $member) {
                            if (!empty($member['email'])
                                && false !== strpos($member['email'], DIRECTORY_DOMAIN)
                                && preg_match('|([a-z]+)@'.DIRECTORY_DOMAIN.'|',$member['email'], $matches)) {

                                $atLargeContact->entry = DirectoryGateway::info($matches[1]);
                                echo $atLargeContact->render('html', $this->template);
                            }
                        }
                    ?>
                </div>
            <?php endif ?>

            <?php if (count($district)): ?>
                <?php
                    // Define some variables for the City Council District Representative
                    if (!empty($district[0]['email'])
                        && false !== strpos($district[0]['email'], DIRECTORY_DOMAIN)
                        && preg_match('|([a-z]+)@'.DIRECTORY_DOMAIN.'|',$district[0]['email'], $matches)) {

                        $districtEntry   = DirectoryGateway::info($matches[1]);
                        $districtFields  = array_merge(['email', 'address'], DirectoryGateway::$phoneNumberFields);
                        $districtRepName = self::escape($districtEntry['firstname']).' '.self::escape($districtEntry['lastname']);
                        $districtImgName = strtolower($districtEntry['lastname']);
                    }
                ?>
                <div         class="myCity-councilDistrict"><h2 class="myCity-electedOfficials-subheading">Your City Council District</h2>
                    <div     class="myCity-councilDistrict-mapContainer">
                        <div class="myCity-councilDistrict-map">
                            <img src="css/img/CD<?= $districtNumber ?>MapImage.png" alt="Map of City Council District <?= $districtNumber ?>" />
                        </div>
                    </div>
                    <div     class="myCity-councilDistrict-details">
                        <img srcset="css/img/<?= $districtImgName ?>-1x.jpg 1x, css/img/<?= $districtImgName ?>-2x.jpg 2x" sizes="299px" src="css/img/<?= $districtImgName ?>-1x.jpg" alt="<?= $districtEntry['displayname'] ?>" />
                        <h3><?= $districtRepName ?></h3>
                        <div class="myCity-councilDistrict-repTitle">District <?= $districtNumber ?> Representative</div>
                        <table class="table-contact">
                        <?php
                            foreach ($districtFields as $field) {
                                if (!empty($districtEntry[$field])) {
                                    $value = self::escape($districtEntry[$field]);
                                    echo "
                                    <tr><th>{$this->_($field)}</th>
                                        <td>$value</td>
                                    </tr>
                                    ";
                                }
                            }
                        ?>
                        </table>
                    </div>
                </div>
            <?php endif ?>

            <div class="myCity-clerk">
                <h2 class="myCity-electedOfficials-subheading"><?= $this->_('clerk'); ?></h2>
                <?php
                   $clerkInfo = DirectoryGateway::info('clerk');
                    $clerkInfo['firstname'] = 'Nicole';
                    $clerkInfo['lastname'] = 'Bolden';
                    $clerkInfo['displayname'] = 'Nicole Bolden';
                    $clerkInfo = DirectoryGateway::info('clerk');
                    $atLargeContact->entry = $clerkInfo;
                    echo $atLargeContact->render('html', $this->template);
                ?>
            </div>
        </div>
    </section>
<?php endif ?>

<section class="uiBlock">
    <header class="uiBlock-header">
        <h2 class="uiBlock-title">Disclaimer</h2>
    </header>
    <div class="uiBlock-content">
        <div class="myCity-disclaimer-text">
            <p>The information reported comes from the City of Bloomington Geographic Information Systems (GIS) and related databases.</p>
            <p>City staff strives to keep complete and accurate information and regrets any errors or omissions. To report missing City of Bloomington addresses or other profile errors, please contact the City of Bloomington GIS Staff at 812-349-3454 or email us at <a href="mailto: gis@bloomington.in.gov">gis@bloomington.in.gov</a>.</p>
        </div>
    </div>
</section>
