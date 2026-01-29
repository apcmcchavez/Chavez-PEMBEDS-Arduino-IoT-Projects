const StatsCard = ({ title, value, unit, bgColor = "bg-blue-50", textColor = "text-blue-600", borderColor = "border-blue-200" }) => {
  return (
    <div className={`${bgColor} ${borderColor} border-l-4 rounded-lg p-6 shadow-sm`}>
      <h3 className="text-sm font-medium text-gray-600 uppercase tracking-wide">{title}</h3>
      <div className="mt-2 flex items-baseline">
        <p className={`text-4xl font-bold ${textColor}`}>{value}</p>
        {unit && <span className="ml-2 text-lg text-gray-500">{unit}</span>}
      </div>
    </div>
  );
};

export default StatsCard;