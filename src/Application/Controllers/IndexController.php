<?php
/**
 * @copyright 2015 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
namespace Application\Controllers;

use Application\Models\Address;
use Application\Models\MasterAddressGateway;

use Blossom\Classes\Template;
use Blossom\Classes\Block;
use Blossom\Classes\Controller;
use Blossom\Classes\Url;

class IndexController extends Controller
{
	public function index()
	{
        $searchForm = new Block('address/searchForm.inc');
		$resultsMap = new Block('address/resultsMap.inc');

		if (empty($_GET['address']) && empty($_GET['address_id'])) {
			$this->template->setFilename('index');
			$this->template->blocks = [
                $searchForm,
                new Block('greeting.inc')
			];
		}
		else {
			$this->template->setFilename('full-width');

			// Handle search results
	        if (!empty($_GET['address'])) {
	            $json = MasterAddressGateway::search($_GET['address']);
	            if ($json && count($json) === 1) {
                    $address = new Address(MasterAddressGateway::info($json[0]['id']));
	            }
	            else {
	                $this->template->blocks = [
                        new Block('address/searchResults.inc', ['results'=>$json])
                    ];
	            }
	        }
	        // Handle single address info
	        elseif (!empty($_GET['address_id'])) {
                $address = new Address(MasterAddressGateway::info((int)$_GET['address_id']));
	        }

	        // If we've got a single address, display the information
	        if (isset($address)) {
                if (!$address->isCurrentAddress()) {
	                $oldAddress = $address;
	                $address    = $oldAddress->getCurrentAddress();
                }

	            if (isset($oldAddress)) {
	                $this->template->blocks[] = new Block('address/oldAddressNotice.inc', ['address'=>$oldAddress]);
	            }

	            $this->template->blocks['pageOverview'][] = new Block('address/tableOfContentsLinks.inc', ['address'=>$address]);
	            $this->template->blocks[]                 = new Block('address/info.inc', ['address'=>$address]);

	            $searchForm->address = $address;
				$resultsMap->address = $address;
	        }
			$this->template->blocks['pageHeader'][] = $resultsMap;
		}

	}
}
