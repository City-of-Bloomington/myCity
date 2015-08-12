<?php
/**
 * @copyright 2015 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
use Blossom\Classes\View;
use Blossom\Classes\Url;
?>
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
        <nav>
            <?php
                $this->addToAsset('scripts', BASE_URI.'/js/menuLauncher.js');
            ?>
            <div class="menuLauncher">Menu</div>
            <div class="menuLinks closed">
                <a href="//bloomington.in.gov/alpha/residents">Residents</a>
                <a href="//bloomington.in.gov/alpha/business">Business</a>
                <a href="//bloomington.in.gov/alpha/visitors">Visitors</a>
                <a href="//bloomington.in.gov/alpha/students">Students</a>
                <a href="//bloomington.in.gov/alpha/government">Government</a>
            </div>
        </nav>

        <a href="//bloomington.in.gov/alpha/" class="cob-siteHeader-logo" title="Home" rel="home" id="logo">
            <img src="//bloomington.in.gov/static/assets/img/bloomington-logo.svg" alt="City of Bloomington, Indiana" />
        </a>
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
