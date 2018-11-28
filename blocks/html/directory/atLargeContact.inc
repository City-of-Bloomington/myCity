<?php
/**
 * @copyright 2015-2018 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @param array $this->entry
 */
$name = parent::escape($this->entry['name']);
$img  = !empty($this->entry['photo'])
      ? "<img src=\"{$this->entry['photo']}\" alt=\"$name\" />"
      : '';
?>

<div class="myCity-atLarge-individual">
    <?= $img; ?>
    <h3><?= $name ?></h3>
    <table class="table-contact">
    <?php
        $contactInfoFields = ['email', 'address', 'phone', 'fax'];
        foreach ($contactInfoFields as $field) {
            if (!empty($this->entry[$field])) {
                $key   = ucfirst($field);
                $value = parent::escape($this->entry[$field]);
                echo "<tr><th>$key</th><td>$value</td></tr>";
            }
        }
    ?>
    </table>
</div>
