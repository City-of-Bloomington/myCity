<?php
/**
 * @copyright 2015-2019 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE
 * @param Address $this->address
 */
$address = $this->address['address'];
?>
<div         class="pageOverview">
    <div     class="pageOverview-container">
        <div class="pageOverview-mainInfo">
            <p><?= $this->_('pageOverview_address', 'messages'); ?></p>
            <address class="pageOverview-address"><?= $address['streetAddress'] ?>

<?= $address['city']?>, <?= $address['state'] ?> <?= $address['zip'] ?></address>
            <?php if($address['latitude'] && $address['longitude']): ?>
                <dl class="pageOverview-latLon">
                    <dt>Latitude</dt>
                    <dd><?= $address['latitude'] ?></dd>
                </dl>
                <dl class="pageOverview-latLon">
                    <dt>Longitude</dt>
                    <dd><?= $address['longitude'] ?></dd>
                </dl>
            <?php endif ?>
        </div>
        <aside>
            <dl class="pageOverview-toc">
                <dt>Learn about</dt>
                <dd><a href="#about-this-address"><?= $this->_('aboutThisAddress'); ?></a></dd>
                <dd><a href="#find-your-government-online"><?= $this->_('governmentLinks'); ?></a></dd>
                <?php if ($address['jurisdiction_name'] == 'Bloomington'): ?>
                    <dd><a href="#elected-officials"><?= $this->_('votingInfo'); ?></a></dd>
                <?php endif ?>
            </dl>
        </aside>
    </div>
</div>
