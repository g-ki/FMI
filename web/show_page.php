<?php
$data = array(
  'webgl' => array(
    'title' => 'Компютърна графика с WebGL',
    'description' => '...',
    'lecturer' => 'доц. П. Бойчев',
  ),
  'go' => array(
    'title' => 'Програмиране с Go',
    'description' => '...',
    'lecturer' => 'Николай Бачийски',
  )
);

// <h1>Компютърна графика с WebGL</h1>
// <h2>доц. П. Бойчев</h2>
// <p>...</p>

function show_page($pageId, $data)
{
  $course = $data[$pageId];
  $template = "";

  if ($course !== NULL) {
    $template = "<h1>{$course['title']}</h1>".PHP_EOL;
    $template .= "<h2>{$course['lecturer']}</h2>".PHP_EOL;
    $template .= "<p>{$course['description']}<p>";
  }

  return $template;
}

// echo show_page('webgl', $data);
