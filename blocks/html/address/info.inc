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
<section id="about-this-address">
    <h2><?= $this->_('aboutThisAddress') ?></h2>

    <div class="myCity-addressInfo-container">
        <?php if(isset($address['latitude']) && isset($address['longitude'])): ?>
            <?php
                if($address['jurisdiction'] == 'Bloomington') {
                    $inOrOut = 'Inside';
                } else {
                    $inOrOut = 'Outside';
                }
            ?>
            <div class="myCity-location-container">
                <div class="myCity-location-cityLimits">
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
                                    $value = View::escape($value);
                                    echo "<dd>$value</dd>";
                                }
                                echo "</dl>";
                            }
                        }
                        if($address['jurisdiction']=='Monroe County') {
                            echo'<p>For more information about this address, see the <a href="http://www.co.monroe.in.us/tsd/gis.aspx">Monroe County GIS website</a>.</p>';
                        }
                    ?>
                </div>
            </div>
        <?php endif; ?>
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

</section>

<section id="find-your-government-online">
    <h2><?= $this->_('governmentLinks'); ?></h2>

    <div class="myCity-govOnline">
        <?php
            global $GOVERNMENTAL_CONTACT_INFO;
            foreach (['state', 'county', 'jurisdiction'] as $region) {
                if($address[$region] != 'IN') {
                    $regionName = $address[$region];
                } else {
                    $regionName = 'Indiana';
                }
                if($address['jurisdiction'] == 'Bloomington' && $region == 'jurisdiction') {
                    $region = 'city';
                }
                echo "
                    <dl>
                        <dt>{$this->_($region)}</dt>
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
</section>

<?php if($address['jurisdiction'] == 'Bloomington'): ?>
    <section id="elected-officials">
        <h2><?= $this->_('votingInfo'); ?></h2>

        <?php $mayorInfo = DirectoryGateway::info('mayor'); ?>
        <?php if(count($mayorInfo)): ?>
            <div class="myCity-mayor">
                <div class="myCity-mayor-photoContainer">
                    <img class="myCity-mayor-photo" srcset="css/img/mayor-1x.jpg 1x, css/img/mayor-2x.jpg 2x" sizes="437px" src="css/img/mayor-1x.jpg" />
                </div>
                <div class="myCity-mayor-details">


                    <div class="myCity-mayor-title"><?= $this->_('mayor'); ?></div>
                    <h2 class="myCity-mayor-name"><?= $mayorInfo['firstname'] ?> <?= $mayorInfo['lastname'] ?></h2>
                    <table class="table-contact">
                        <tr>
                            <th>Email</th>
                            <td><?= $mayorInfo['email'] ?></td>
                        </tr>
                        <tr>
                            <th>Mailing Address</th>
                            <td>Office Of The Mayor<br />401 N Morton St<br />Bloomington, IN 47404</td>
                        </tr>
                        <tr>
                            <th>Telephone</th>
                            <td><?= $mayorInfo['office'] ?></td>
                        </tr>
                    </table>
                    <div class="myCity-mayor-biography">
                        <h3>About the Mayor</h3>
                        <p>Mark Kruzan served as an Adjunct Professor at the IU School of Public and Environmental Affairs starting in 1990, where he taught &ldquo;Indiana Politics &amp; Policy&rdquo;. In 1986, he was elected as State Representative for Bloomington. In 1994, he was appointed House Minority Whip. Two years later, he was elected Majority Leader of the Indiana House of Representatives by his colleagues&mdash;a post he held until he decided not to run for re-election in 2002.</p>
                        <p>He was elected Mayor of Bloomington in November 2003. As Mayor, he leads a city with incredible opportunities ahead of it&mdash;and he works hard to address its challenges.</p>
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

                $districtName = View::escape($districtName);
                $districtNumber = View::escape(filter_var($districtName, FILTER_SANITIZE_NUMBER_INT));
            }
        ?>
        <?php if(count($atLarge)): ?>
            <div class="myCity-atLarge">
                <h2><?= $this->_('atLarge'); ?></h2>
                <?php
                    foreach ($atLarge as $member) {
                        if (
                            !empty($member['email'])
                            && false !== strpos($member['email'], DIRECTORY_DOMAIN)
                            && preg_match('|([a-z]+)@'.DIRECTORY_DOMAIN.'|',$member['email'], $matches)
                        ) {
                            $atLargeContact->entry = DirectoryGateway::info($matches[1]);
                            echo $atLargeContact->render('html', $this->template);
                        }
                    }
                ?>
            </div>
        <?php endif ?>


        <?php if(count($district)): ?>
            <?php
                // Define some variables for the City Council District Representative
                if (
                    !empty($district[0]['email'])
                    && false !== strpos($district[0]['email'], DIRECTORY_DOMAIN)
                    && preg_match('|([a-z]+)@'.DIRECTORY_DOMAIN.'|',$district[0]['email'], $matches)
                ) {
                    $districtEntry = DirectoryGateway::info($matches[1]);
                    $districtFields = array_merge(['email', 'address'], DirectoryGateway::$phoneNumberFields);
                    $districtRepName = View::escape($districtEntry['firstname']).' '.View::escape($districtEntry['lastname']);
                    $districtImgName = strtolower($districtEntry['lastname']);
                }
            ?>
            <div class="myCity-councilDistrict">
                <h2>Your City Council District</h2>
                <div class="myCity-councilDistrict-mapContainer">
                    <div class="myCity-councilDistrict-map">
                        <img src="css/img/CD<?= $districtNumber ?>MapImage.png" alt="Map of City Council District <?= $districtNumber ?>" />
                    </div>
                </div>
                <div class="myCity-councilDistrict-details">
                    <img srcset="css/img/<?= $districtImgName ?>-1x.jpg 1x, css/img/<?= $districtImgName ?>-2x.jpg 2x" sizes="299px" src="css/img/<?= $districtImgName ?>-1x.jpg" alt="<?= $districtEntry['displayname'] ?>" />
                    <h3><?= $districtRepName ?></h3>
                    <div class="myCity-councilDistrict-repTitle">District <?= $districtNumber ?> Representative</div>
                    <table class="table-contact">
                        <?php
                            foreach ($districtFields as $field) {
                                if (!empty($districtEntry[$field])) {
                                    $value = View::escape($districtEntry[$field]);
                                    echo "
                                        <tr>
                                            <th>{$this->_($field)}</th>
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
            <h2><?= $this->_('clerk'); ?></h2>
            <?php
                $clerkInfo = DirectoryGateway::info('clerk');
                $clerkInfo['firstname'] = 'Regina';
                $clerkInfo['lastname'] = 'Moore';
                $clerkInfo['displayname'] = 'Regina Moore';
                $atLargeContact->entry = $clerkInfo;
                echo $atLargeContact->render('html', $this->template);
            ?>

        </div>
    </section>
<?php endif ?>

<section>
    <h2>Disclaimer</h2>
    <div class="myCity-disclaimer-text">
        <p>The information reported comes from the City of Bloomington Geographic Information Systems (GIS) and related databases.</p>
        <p>City staff strives to keep complete and accurate information and regrets any errors or omissions. To report missing City of Bloomington addresses or other profile errors, please contact the City of Bloomington GIS Staff at 349-3454 or email us at <a href="mailto: gis@bloomington.in.gov">gis@bloomington.in.gov</a>.</p>
    </div>

</section>
