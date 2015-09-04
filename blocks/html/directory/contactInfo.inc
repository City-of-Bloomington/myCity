<?php
/**
 * @copyright 2015 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param entry $this->entry
 */
use Application\Models\DirectoryGateway;
use Blossom\Classes\View;

$name = !empty(    $this->entry['displayname'])
    ? View::escape($this->entry['displayname'])
    : View::escape("{$this->entry['firstname']} {$this->entry['lastname']}");
$contactInfoFields = array_merge(['email', 'address'], DirectoryGateway::$phoneNumberFields);
$imgName = strtolower(View::escape($this->entry['lastname']));
?>




<img srcset="css/img/<?= $imgName ?>-1x.jpg 1x, css/img/<?= $imgName ?>/-2x.jpg 2x" sizes="299px" src="css/img/<?= $imgName ?>-1x.jpg" alt="<?= $name ?>" />
<h3><?= $name ?></h3>
<table class="contact">
    <?php
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
