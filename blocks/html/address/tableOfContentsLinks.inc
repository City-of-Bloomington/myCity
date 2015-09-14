<?php
/**
 * @copyright 2015 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @param Address $this->address
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */

$address = $this->address;
?>
<div class="myCity-pageOverview">
    <div class="myCity-pageOverview-container">
        <div class="myCity-pageOverview-mainInfo">
            <p><?= $this->_('pageOverview_address', 'messages'); ?></p>
            <address class="myCity-pageOverview-address"><?= $address['streetAddress'] ?>

<?= $address['city']?>, <?= $address['state'] ?> <?= $address['zip'] ?></address>
            <?php if($address['latitude'] && $address['longitude']): ?>
                <dl class="myCity-pageOverview-latLon">
                    <dt>Latitude</dt>
                    <dd><?= $address['latitude'] ?></dd>
                </dl>
                <dl class="myCity-pageOverview-latLon">
                    <dt>Longitude</dt>
                    <dd><?= $address['longitude'] ?></dd>
                </dl>
            <?php endif ?>
        </div>
        <aside>
            <dl class="myCity-pageOverview-toc">
                <dt>Learn about</dt>
                <dd><a href="#about-this-address"><?= $this->_('aboutThisAddress'); ?></a></dd>
                <dd><a href="#find-your-government-online"><?= $this->_('governmentLinks'); ?></a></dd>
                <dd><a href="#elected-officials"><?= $this->_('votingInfo'); ?></a></dd>
            </dl>
        </aside>
    </div>
</div>
