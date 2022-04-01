<?php
/**
 * @copyright 2022 City of Bloomington, Indiana
 * @license https://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE
 */
declare (strict_types=1);
namespace Web\Views;

use Web\View;

class InfoView extends View
{
    public function __construct(array $address,
                                array $schools,
                                array $parks,
                                array $playgrounds)
    {
        parent::__construct();

        global $CONTACT_INFO;
        $this->vars = [
            'address'      => $address['address' ],
            'location'     => $address['location'],
            'purposes'     => $address['purposes'] ?? [],
            'contact_info' => $CONTACT_INFO,
            'schools'      => $schools,
            'parks'        => $parks,
            'playgrounds'  => $playgrounds
        ];
    }

    public function render(): string
    {
        return $this->twig->render("{$this->outputFormat}/address/info.twig", $this->vars);
    }
}
