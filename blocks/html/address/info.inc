<?php
/**
 * @copyright 2015-2019 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE
 * @param Address $this->address
 */
use Application\Models\MasterAddressGateway;
use Application\Models\CityCouncilGateway;
use Application\Models\DirectoryGateway;

use Blossom\Classes\Block;

global $CONTACT_INFO;

$address = $this->address;
?>
<section    class="uiBlock" id="about-this-address">
    <header class="uiBlock-header">
        <h2 class="uiBlock-title"><?= $this->_('aboutThisAddress') ?></h2>
    </header>
    <div    class="uiBlock-content">
        <div class="myCity-addressInfo">
            <?php if(isset($address['address']['latitude']) && isset($address['address']['longitude'])): ?>
                <?php
                    $inOrOut = $address['address']['jurisdiction_name'] === 'Bloomington'
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
                        if ($address['address']['jurisdiction_name'] === 'Monroe County') {
                            echo "
                            <p>For more information about this address, see the
                                <a href=\"http://www.co.monroe.in.us/tsd/gis.aspx\">
                                Monroe County GIS website
                                </a>.
                            </p>
                            ";
                        }
                    ?>
                    <?php if (!empty($address['address']['township_name'])): ?>
                        <dl class="myCity-addressInfo-keyValuePair modLocation">
                            <dt><?= $this->_('township') ?></dt>
                            <dd><?= $address['address']['township_name'] ?></dd>
                        </dl>
                    <?php endif ?>
                    </div>
                </div>
            <?php endif; ?>
            <?php
                if (isset($address['trashDay'])) {
                    global $SANITATION_SCHEDULE;

                    $trashDay    = ucfirst(strtolower($address['trashDay']));
                    $recycleWeek = $address['recycleWeek'];
                    $url         = $SANITATION_SCHEDULE[$recycleWeek][$trashDay];
                    $details     = sprintf($this->_('sanitationDetails', 'messages'), '<a href="/trash">', '</a>');

                    echo "
                    <div    class=\"myCity-trash-container\">
                        <dl class=\"myCity-addressInfo-keyValuePair modTrashDay\">
                            <dt>{$this->_('trashDay')}</dt>
                            <dd>$trashDay</dd>
                        </dl>
                        <dl class=\"myCity-addressInfo-keyValuePair modRecycleWeek\">
                            <dt>{$this->_('nextRecyclePickup')}</dt>
                            <dd><a href=\"$url\">Week $recycleWeek</a></dd>
                        </dl>
                        <p class=\"myCity-trash-details\">$details</p>
                    </div>
                    ";
                }
            ?>
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

<section    class="uiBlock" id="find-your-government-online">
    <header class="uiBlock-header">
        <h2 class="uiBlock-title"><?= $this->_('governmentLinks'); ?></h2>
    </header>
    <div    class="uiBlock-content">
        <div class="myCity-govOnline">
            <?php
                global $GOVERNMENTAL_CONTACT_INFO;
                foreach (['state', 'county', 'jurisdiction_name'] as $region) {
                    $regionName = $address['address'][$region] === 'IN'
                        ? 'Indiana'
                        : $address['address'][$region];

                    if ($address['address']['jurisdiction_name'] === 'Bloomington' && $region === 'jurisdiction_name') {
                        $region = 'city';
                    }
                    echo "
                    <dl><dt>{$this->_($region)}</dt>
                        <dd>$regionName</dd>
                    ";
                    if (array_key_exists($address['address'][$region], $GOVERNMENTAL_CONTACT_INFO)) {
                        echo '<dd><dl>';
                        foreach ($GOVERNMENTAL_CONTACT_INFO[$address['address'][$region]]['online'] as $type=>$link) {
                            $label = ucfirst($this->_($type));
                            echo "
                            <dt>$label:</dt>
                            <dd><a href=\"$link[url]\">$link[text]</a></dd>
                            ";

                        }
                        echo '</dl></dd>';
                        echo '<dd><dl>';
                        foreach ($GOVERNMENTAL_CONTACT_INFO[$address['address'][$region]]['offline'] as $type=>$info) {
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

<?php if ($address['address']['jurisdiction_name'] == 'Bloomington'): ?>
    <section    class="uiBlock" id="elected-officials">
        <header class="uiBlock-header">
            <h2 class="uiBlock-title"><?= $this->_('votingInfo'); ?></h2>
        </header>
        <div    class="uiBlock-content">
            <?php $mayorInfo = $CONTACT_INFO['mayor']; ?>
            <div         class="myCity-mayor">
                <div     class="myCity-mayor-photoContainer">
                    <img class="myCity-mayor-photo" src="<?= $mayorInfo['photo']; ?>" />
                </div>
                <div     class="myCity-mayor-details">
                    <div class="myCity-mayor-title"><?= $this->_('mayor'); ?></div>
                    <h2  class="myCity-mayor-name"><?= $mayorInfo['name'] ?></h2>
                    <table class="table-contact">
                        <tr><th>Email</th>
                            <td><?= $mayorInfo['email'] ?></td>
                        </tr>
                        <tr><th>Mailing Address</th>
                            <td><?= $mayorInfo['address']; ?></td>
                        </tr>
                        <tr><th>Telephone</th>
                            <td><?= $mayorInfo['phone'] ?></td>
                        </tr>
                    </table>
                    <div class="myCity-mayor-biography">
                        <h3>About the Mayor</h3>
                        <p>John has worked extensively as a public servant in Democratic government, leading two state agencies, advising a Governor and Lieutenant Governor, and serving as an elected official.  As the Secretary of the Indiana Family and Social Services Administration, he oversaw the implementation of Medicaid and welfare programs, services for the elderly, disabled, mentally ill, and children at risk, and state-wide community development and housing programs – all executed by a staff of 10,000 Hoosiers with an annual budget of $6 billion. Earlier he served as Commissioner of the Indiana Department of Environmental Management, the agency tasked with the statewide protection of Indiana’s air, water and land. John served as an elected member of the Board of Trustees for the Monroe County Community School Corporation. Throughout his time in Bloomington, John has served on many state and local commissions and boards, including chairing the Bloomington Commission on Sustainability and the Shalom Community Center board, as well as national boards such as the National Community Land Trust Network.</p>
                    </div>
                </div>
            </div>
            <?php
                $atLargeContact = new Block('directory/atLargeContact.inc');
                $districtMember = '';
                $atLargeMembers = '';
                if (!empty(           $purposes['councilDistrict'])) {
                    $districtName   = $purposes['councilDistrict'][0];
                    $districtRep    = $CONTACT_INFO['council'][$districtName];
                    $atLargeReps    = $CONTACT_INFO['council']['At-Large'   ];
                    $districtNumber = self::escape(filter_var($districtName, FILTER_SANITIZE_NUMBER_INT));
                }
            ?>
            <?php if ($atLargeReps): ?>
                <div    class="myCity-atLarge">
                    <h2 class="myCity-electedOfficials-subheading"><?= $this->_('atLarge'); ?></h2>
                    <?php
                        foreach ($atLargeReps as $rep) {
                            $atLargeContact->entry = $rep;
                            echo $atLargeContact->render('html', $this->template);
                        }
                    ?>
                </div>
            <?php endif ?>

            <?php if ($districtRep): ?>
                <?php
                    // Define some variables for the City Council District Representative
                    $districtRepName = parent::escape($districtRep['name']);
                    $districtImg     = !empty($districtRep['photo'])
                                     ? "<img src=\"$districtRep[photo]\" alt=\"$districtRepName\" />"
                                     : '';
                ?>
                <div         class="myCity-councilDistrict"><h2 class="myCity-electedOfficials-subheading">Your City Council District</h2>
                    <div     class="myCity-councilDistrict-mapContainer">
                        <div class="myCity-councilDistrict-map">
                            <img src="css/img/CD<?= $districtNumber ?>MapImage.png" alt="Map of City Council District <?= $districtNumber ?>" />
                        </div>
                    </div>
                    <div     class="myCity-councilDistrict-details">
                        <?= $districtImg; ?>
                        <h3><?= $districtRepName ?></h3>
                        <div class="myCity-councilDistrict-repTitle">District <?= $districtNumber ?> Representative</div>
                        <table class="table-contact">
                        <?php
                            foreach (['email', 'address', 'phone', 'fax'] as $field) {
                                if (!empty($districtRep[$field])) {
                                    $key   = ucfirst($field);
                                    $value = self::escape($districtRep[$field]);
                                    echo "<tr><th>$key</th><td>$value</td></tr>";
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
                    $atLargeContact->entry = $CONTACT_INFO['clerk'];
                    echo $atLargeContact->render('html', $this->template);
                ?>
            </div>
        </div>
    </section>
<?php endif ?>

<section    class="uiBlock">
    <header class="uiBlock-header">
        <h2 class="uiBlock-title">Disclaimer</h2>
    </header>
    <div    class="uiBlock-content">
        <div class="myCity-disclaimer-text">
            <p>The information reported comes from the City of Bloomington Geographic Information Systems (GIS) and related databases.</p>
            <p>City staff strives to keep complete and accurate information and regrets any errors or omissions. To report missing City of Bloomington addresses or other profile errors, please contact the City of Bloomington GIS Staff at 812-349-3454 or email us at <a href="mailto: gis@bloomington.in.gov">gis@bloomington.in.gov</a>.</p>
        </div>
    </div>
</section>
