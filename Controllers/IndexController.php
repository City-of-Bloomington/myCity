<?php
/**
 * @copyright 2015 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
namespace Application\Controllers;

use Application\Models\MasterAddressGateway;

use Blossom\Classes\Block;
use Blossom\Classes\Controller;
use Blossom\Classes\Url;

class IndexController extends Controller
{
	public function index()
	{
        $this->template->blocks[] = new Block('address/searchForm.inc');

        if (!empty($_GET['address_id'])) {
            $address = MasterAddressGateway::info($_GET['address_id']);
            $this->template->blocks[] = new Block('address/info.inc', ['address'=>$address]);
        }
        if (!empty($_GET['address'])) {
            $json = MasterAddressGateway::search($_GET['address']);
            $this->template->blocks[] = new Block('address/searchResults.inc', ['results'=>$json]);
        }
	}
}
