<?php
/**
 * @copyright 2022-2024 City of Bloomington, Indiana
 * @license https://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE
 */
declare (strict_types=1);
namespace Web\Info;

class View extends \Web\View
{
    public function __construct(array $address)
    {
        parent::__construct();

        global $CONTACT_INFO;
        $this->vars = [
            'address'      => $address['address' ],
            'location'     => $address['location'],
            'purposes'     => $address['purposes'] ?? [],
            'contact_info' => $CONTACT_INFO
        ];
    }

    public function render(): string
    {
        return $this->twig->render("{$this->outputFormat}/address/info.twig", $this->vars);
    }
}
