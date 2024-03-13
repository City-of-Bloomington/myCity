<?php
/**
 * @copyright 2024 City of Bloomington, Indiana
 * @license https://www.gnu.org/licenses/agpl.txt GNU/AGPL, see LICENSE
 */
declare (strict_types=1);
namespace Web\Search;

class ResultsOnlyView extends \Web\View
{
    public function __construct(array $results)
    {
        parent::__construct();

        $this->vars = ['results' => $results];
    }

    public function render(): string
    {
        return $this->twig->render("{$this->outputFormat}/address/partials/searchResults.twig", $this->vars);
    }
}
