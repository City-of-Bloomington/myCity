<?php
/**
 * @copyright 2024 City of Bloomington, Indiana
 * @license http://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE
 */
declare (strict_types=1);
namespace Web\Help;

use Web\Services\MasterAddressGateway;

class Controller extends \Web\Controller
{
    public function __invoke(array $params): \Web\View
    {
        return new View();
    }
}
