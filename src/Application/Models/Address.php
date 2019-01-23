<?php
/**
 * @copyright 2015-2019 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE
 */
namespace Application\Models;

class Address implements \ArrayAccess
{
    public $data = [];

    public function __construct(array $data)
    {
        $this->data = $data;
        $this->data['address']['county'] = DEFAULT_COUNTY;
    }

    public function __get($field)
    {
        if (!empty($this->data[$field])) { return $this->data[$field]; }
    }

    public function isCurrentAddress(): bool
    {
        foreach ($this->data['locations'] as $l) {
            if ($l['active']) {
                if ($l['address_id'] == $this->data['address']['id']) {
                    return true;
                }
            }
        }
        return false;
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
    public function getCurrentAddress(): Address
    {
        foreach ($this->data['locations'] as $location) {
            if ($location['active']) {
                return ($location['address_id'] == $this->data['address']['id'])
                    ? $this
                    : new Address(MasterAddressGateway::info((int)$location['address_id']));
            }
        }
    }

    /**
     * Returns the address purposes in a more usable form
     *
     * Returns an array using the possible purpose types as the key.
     * Each key's value is an array of all the values from the adress
     * for that purpose type.
     *
     * @return array
     */
    public function getPurposeValuesByType()
    {
        $out = [];
        if (  !empty($this->data['purposes'])) {
            foreach ($this->data['purposes'] as $purpose) {
                if (array_key_exists($purpose['purpose_type'], MasterAddressGateway::$purposeMap)) {
                    $variableName = MasterAddressGateway::$purposeMap[$purpose['purpose_type']];
                    $out[$variableName][] = $purpose['name'];
                }
            }
        }
        return $out;
    }

    //------------------------------------------------
    // ArrayAccess functions
    //------------------------------------------------
    public function offsetExists($offset) { return isset($this->data[$offset]); }
    public function offsetGet   ($offset) { return $this->data[$offset]; }
    public function offsetUnset ($offset) { unset($this->data[$offset]); }
    public function offsetSet   ($offset, $value) { $this->data[$offset] = $value; }
}
