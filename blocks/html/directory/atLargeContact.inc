<?php
/**
 * @copyright 2015-2018 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @param entry $this->entry
 */
use Application\Models\DirectoryGateway;

$name = !empty(    $this->entry['displayname'])
      ? parent::escape($this->entry['displayname'])
      : parent::escape("{$this->entry['firstname']} {$this->entry['lastname']}");
$img  = !empty($this->entry['photo'])
      ? "<img src=\"{$this->entry['photo']}\" alt=\"$name\" />"
      : '';
?>

<div class="myCity-atLarge-individual">
    <?= $img; ?>
    <h3><?= $name ?></h3>
    <table class="table-contact">
        <?php
        $contactInfoFields = array_merge(['email', 'address'], DirectoryGateway::$phoneNumberFields);
        foreach ($contactInfoFields as $field) {
            if (!empty($this->entry[$field])) {
                $value = parent::escape($this->entry[$field]);
                $field = $field == 'pager' ? 'Phone' : $field;
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
