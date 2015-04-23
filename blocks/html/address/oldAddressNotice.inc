<?php
/**
 * @copyright 2015 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param Address $this->address
 */
?>
<div class="notice">
    <h2><?= $this->_('oldAddress'); ?></h2>
    <p>
    <?php
        echo sprintf($this->_('oldAddressNotice', 'messages'), $this->address['streetAddress']);
    ?>
    </p>
</div>