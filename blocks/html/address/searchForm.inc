<?php
/**
 * @copyright 2015 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
use Blossom\Classes\View;

$address = !empty($_GET['address']) ? View::escape($_GET['address']) : '';
?>
<form method="get" action="<?php echo BASE_URI; ?>">
    <fieldset>
        <label  for="address"><?= $this->_('address'); ?></label>
        <input name="address" id="address" value="<?= $address; ?>" />
        <button type="submit" class="search"><?= $this->_('search'); ?></button>
    </fieldset>
</form>
