<?php
/**
 * @copyright 2015 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param Address $this->address
 */
use Blossom\Classes\View;
if (isset($this->address)) {
    $address    = $this->address['streetAddress'];
}
else {
    $address = !empty($_GET['address']) ? View::escape($_GET['address']) : '';
}
?>

<form method="get" action="<?php echo BASE_URI; ?>" class="myCity-searchForm">
    <label  for="address"><?= $this->_('address'); ?></label>
    <input name="address" id="address" value="<?= $address; ?>" placeholder="Search for your address" />
    <button type="submit" class="search"><?= $this->_('search'); ?></button>
</form>
