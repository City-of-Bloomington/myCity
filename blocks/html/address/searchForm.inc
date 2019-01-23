<?php
/**
 * @copyright 2015-2019 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE
 * @param Address $this->address
 */
use Blossom\Classes\View;
if (isset($this->address)) {
    $address = $this->address['address']['streetAddress'];
}
else {
    if (!empty($_GET['address'])) {
        $address = View::escape($_GET['address']);
    }
}
?>
<form method="get" action="<?= BASE_URI; ?>" class="myCity-searchForm">
    <label  for="address"><?= $this->_('address'); ?></label>
    <input name="address" id="address" value="<?= $address; ?>" placeholder="Search for your address" />
    <button type="submit" class="search"><?= $this->_('search'); ?></button>
</form>
