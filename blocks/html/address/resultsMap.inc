<?php
/**
 * @copyright 2015-2019 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE
 * @param Address $this->address
 */
use Blossom\Classes\View;

if (isset($this->address)) {
    $lat        = $this->address['address']['latitude'];
    $lon        = $this->address['address']['longitude'];
    $data_title = "data-title=\"{$this->address['address']['streetAddress']}\"";
    $address    = $this->address['address']['streetAddress'];
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
