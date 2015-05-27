<?php
/**
 * @copyright 2015 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>

 * @param Address $this->address
*/

use Blossom\Classes\View;
use Blossom\Classes\Url;
?>
<header class="cob-siteHeader">
    <div class="cob-siteHeader-container">
        <div class="region region-header-site">
            <div id="block-search-form" class="block block-search">
                <div class="content">
                    <form action="http://rogue.bloomington.in.gov/drupal2" method="post" id="search-block-form" accept-charset="UTF-8">
                        <div>
                            <div class="form-item form-type-textfield form-item-search-block-form">
                                <label for="edit-search-block-form--2">How can we help you today? </label>
                                <input title="Enter the terms you wish to search for." placeholder="Search Bloomington.in.gov" type="text" id="edit-search-block-form--2" name="search_block_form" value="" size="15" maxlength="128" class="form-text" />
                            </div>
                            <div class="form-actions form-wrapper" id="edit-actions">
                                <input type="submit" id="edit-submit" name="op" value="Search" class="form-submit" />
                            </div>
                            <input type="hidden" name="form_build_id" value="form-P53a_GlmwvSlPfq1Yw3UnfXhak1ci-vjgFaplZ6qrBw" />
                            <input type="hidden" name="form_id" value="search_block_form" />
                        </div>
                    </form>
                </div>
            </div>
        </div>
        <nav>
            <?php
                $this->addToAsset('scripts', BASE_URI.'/js/menuLauncher.js');
            ?>
            <div class="menuLauncher">Menu</div>
            <div class="menuLinks closed">
                <a href="http://rogue.bloomington.in.gov/drupal2/residents">Residents</a>
                <a href="http://rogue.bloomington.in.gov/drupal2/taxonomy/term/2">Business</a>
                <a href="http://rogue.bloomington.in.gov/drupal2/taxonomy/term/13">Visitors</a>
                <a href="http://rogue.bloomington.in.gov/drupal2/taxonomy/term/3">Students</a>
                <a href="http://rogue.bloomington.in.gov/drupal2/taxonomy/term/4">Government</a>
            </div>
        </nav>

        <a href="http://rogue.bloomington.in.gov/drupal2/" class="cob-siteHeader-logo" title="Home" rel="home" id="logo">
            <img src="http://rogue.bloomington.in.gov/drupal2/themes/cob/logo.svg" alt="City of Bloomington, Indiana" />
        </a>
    </div>
</header>
<header class="cob-pageHeader ">
    <?php
        if (isset($this->address)) {
            $lat   = $this->address['latitude'];
            $lon   = $this->address['longitude'];
            $title = $this->address['streetAddress'];
        } else {
            $lat = DEFAULT_LATITUDE;
            $lon = DEFAULT_LONGITUDE;
        }
    ?>
    <div class="cob-pageHeader-mapCanvas" data-latitude="<?= $lat ?>" data-longitude="<?= $lon ?>" <?= $title ? 'data-title="'.$title.'"' : '' ?> id="map-canvas"></div>
    <?php 
        $address = !empty($_GET['address']) ? View::escape($_GET['address']) : '';
    ?>
    <form method="get" action="<?php echo BASE_URI; ?>" class="myCity-searchForm">
        <label  for="address"><?= $this->_('address'); ?></label>
        <input name="address" id="address" value="<?= $address; ?>" />
        <button type="submit" class="search"><?= $this->_('search'); ?></button>
    </form>
</header>