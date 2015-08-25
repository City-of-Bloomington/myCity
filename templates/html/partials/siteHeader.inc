<?php
/**
 * @copyright 2015 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
use Blossom\Classes\View;
use Blossom\Classes\Url;
?>

<?php include(ASSETS_HOME."/html/alphaHeader.html"); ?>

<header class="cob-siteHeader">
    <div class="cob-siteHeader-container">
        <div class="region region-header-site">
            <div id="block-search-form" class="block block-search">
                <div class="content">
                    <form action="//bloomington.in.gov/alpha/search" method="post" id="search-block-form" accept-charset="UTF-8">
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
        <?php
            $this->addToAsset('scripts', BASE_URI.'/js/menuLauncher.js');
            include(ASSETS_HOME.'/html/cob-siteHeader-menu.html');
            include(ASSETS_HOME.'/html/cob-siteHeader-logo.html');
        ?>
    </div>
</header>
<header class="cob-pageHeader ">
    <?php
        echo $this->includeBlocks('pageHeader');
    ?>
    <div class="cob-pageOverview">
        <div class="cob-pageOverview-container">
        <?php
            echo $this->includeBlocks('pageOverview');
        ?>
        </div>
    </div>
</header>
