<?php
/**
 * @copyright 2022 City of Bloomington, Indiana
 * @license https://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE
 */
declare (strict_types=1);
namespace Web\Views;

use Web\View;

class SearchView extends View
{
    public function __construct(?string $query    = null,
                                ?array  $response = null)
    {
        parent::__construct();

        $this->vars = [
            'query'   => $query,
            'results' => $response
        ];
    }
    public function render(): string
    {
        return $this->twig->render("{$this->outputFormat}/address/searchView.twig", $this->vars);
    }
}
