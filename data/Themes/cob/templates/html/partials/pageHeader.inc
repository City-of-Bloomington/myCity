<?php
/**
 * @copyright 2015-2018 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 */
use Blossom\Classes\View;
use Blossom\Classes\Url;

$this->addToAsset('scripts', BASE_URI.'/js/menuLauncher.js');
?>
<header class="siteHeader">
    <div class="siteHeader-container">
        <?php
            $this->addToAsset('scripts', BASE_URI.'/js/menuLauncher.js');
        ?>
        <a href="//bloomington.in.gov/" class="cob-siteHeader-logo" title="Home" rel="home" id="logo">
            <img src="//bloomington.in.gov/static/assets/img/bloomington-logo.svg"
                alt="City of Bloomington, Indiana" />
        </a>
    </div>
</header>
<header class="cob-pageHeader">
    <?= $this->includeBlocks('pageHeader'); ?>
    <?= $this->includeBlocks('pageOverview'); ?>
</header>
