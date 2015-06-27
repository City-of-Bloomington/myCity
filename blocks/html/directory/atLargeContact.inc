<?php
/**
 * @copyright 2015 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Dan Hiester <hiesterd@bloomington.in.gov>
 * @param entry $this->entry
 */
use Application\Models\DirectoryGateway;
use Blossom\Classes\View;

$name = !empty(    $this->entry['displayname'])
    ? View::escape($this->entry['displayname'])
    : View::escape("{$this->entry['firstname']} {$this->entry['lastname']}");
?>

<div class="myCity-atLarge-individual">
    <h3><?= $name ?></h3>
    <table class="table-contact">
        <?php
        $contactInfoFields = array_merge(['email', 'address'], DirectoryGateway::$phoneNumberFields);
        foreach ($contactInfoFields as $field) {
            if (!empty($this->entry[$field])) {
                $value = View::escape($this->entry[$field]);
                echo "
                <tr>
                    <th>{$this->_($field)}</th>
                    <td>$value</td>
                </tr>
                ";
            }
        }
        ?>
    </table>
</div>
