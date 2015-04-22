<?php
/**
 * Data object for Address information
 *
 * This class handles translating the JSON responses from Master Address
 *
 * @copyright 2015 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE.txt
 * @author Cliff Ingham <inghamn@bloomington.in.gov>
 */
namespace Application\Models;

class Address
{
    public function __construct(stdClass $json)
    {
    }
}