<?php
/**
 * @copyright 2015 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 * @param array $this->results JSON array of result objects
 */
if (!$this->results) {
    echo "<h2>{$this->_('no_results_found', 'messages')}</h2>";
}
else {
?>
<h2><?= $this->_(['address', 'addresses', 2]); ?></h2>
<table>
    <thead>
        <tr><th><?= $this->_('address'); ?></th>
            <th><?php
                    echo $this->_('city');
                    echo $this->_('state');
                    echo $this->_('zip');
                ?>
            </th>
        </tr>
    </thead>
    <tbody>
    <?php
        foreach ($this->results as $address) {
            $url = BASE_URI.'?address_id='.$address['id'];
            echo "
            <tr><td><a href=\"$url\">$address[streetAddress]</a></td>
                <td>$address[city] $address[state] $address[zip]</td>
            </tr>
            ";
        }
    ?>
    </tbody>
</table>
<?php
}
