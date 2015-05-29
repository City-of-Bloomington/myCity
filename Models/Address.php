<?php
/**
 * @copyright 2015 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
namespace Application\Models;

class Address implements \ArrayAccess
{
    public $data = [];

    /**
     * @param int|array $address_id
     */
    public function __construct($address)
    {
        $this->data = is_array($address)
            ? $address
            : MasterAddressGateway::info($address);
    }

    public function __get($field)
    {
        if (!empty($this->data[$field])) { return $this->data[$field]; }
    }

    /**
     * Returns the current address for any address
     *
     * Addresses get changed all the time in GIS.  When
     * we're working with an address that is no longer active,
     * we want to be able to load the current address information.
     *
     * Calling this on an address that is already the current address
     * will just return $this
     *
     * @return Address
     */
    public function getCurrentAddress()
    {
        foreach ($this->data['locations'] as $location) {
            if ($location['active']) {
                if ($location['address_id'] == $this->data['id']) {
                    return $this;
                }
                else {
                    return new Address($location['address_id']);
                }
            }
        }
    }

    //------------------------------------------------
    // ArrayAccess functions
    //------------------------------------------------
    public function offsetExists($offset) { return isset($this->data[$offset]); }
    public function offsetGet   ($offset) { return $this->data[$offset]; }
    public function offsetUnset ($offset) { unset($this->data[$offset]); }
    public function offsetSet   ($offset, $value) { $this->data[$offset] = $value; }
}