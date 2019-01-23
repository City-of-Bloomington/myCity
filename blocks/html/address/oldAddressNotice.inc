<?php
/**
 * @copyright 2015-2019 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE
 * @param Address $this->address
 */
?>
<div class="notice">
    <h2><?= $this->_('oldAddress'); ?></h2>
    <p>
    <?php
        echo sprintf($this->_('oldAddressNotice', 'messages'), $this->address['address']['streetAddress']);
    ?>
    </p>
</div>
