<?php
/**
 * @copyright 2015 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
namespace Application\Controllers;

use Application\Models\Address;
use Application\Models\MasterAddressGateway;

use Blossom\Classes\Block;
use Blossom\Classes\Controller;
use Blossom\Classes\Url;

class IndexController extends Controller
{
	public function index()
	{
        $searchForm = new Block('address/searchForm.inc');

        // Handle search results
        if (!empty($_GET['address'])) {
            $json = MasterAddressGateway::search($_GET['address']);
            if (count($json) === 1) {
                $address = new Address($json[0]);
            }
            else {
                $this->template->blocks[] = new Block('address/searchResults.inc', ['results'=>$json]);
            }
        }
        // Handle single address info
        elseif (!empty($_GET['address_id'])) {
            $address = new Address($_GET['address_id']);
        }

        // If we've got a single address, display the information
        if (isset($address)) {
            if (!$address['active'] || $address['active'] != 'yes') {
                $oldAddress = $address;
                $address    = $oldAddress->getCurrentAddress();
            }
            if (isset($oldAddress)) {
                $this->template->blocks[] = new Block('address/oldAddressNotice.inc', ['address'=>$oldAddress]);
            }
            
            $this->template->blocks['pageOverview'][] = new Block('address/tableOfContentsLinks.inc');
            $this->template->blocks[]                 = new Block('address/info.inc', ['address'=>$address]);

            $searchForm->address = $address;
        }
        $this->template->blocks['pageHeader'][] = $searchForm;
	}
}
