<?php
/**
 * @copyright 2015-2018 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE
 * @param Address $this->address
 */
use Blossom\Classes\View;

if (isset($this->address)) {
    $lat        = $this->address['latitude'];
    $lon        = $this->address['longitude'];
    $data_title = "data-title=\"{$this->address['streetAddress']}\"";
    $address    = $this->address['streetAddress'];
}
else {
    $lat = DEFAULT_LATITUDE;
    $lon = DEFAULT_LONGITUDE;
    $data_title = '';
    $address = !empty($_GET['address']) ? View::escape($_GET['address']) : '';
}
?>
<div class="myCity-pageHeader-mapCanvas"
    data-latitude="<?= $lat ?>"
    data-longitude="<?= $lon ?>"
    <?= $data_title; ?> id="map-canvas"></div>

<?php $this->_include('address/searchForm.inc'); ?>
