import { useState, useEffect } from 'react';
import StatsCard from './StatsCard';
import EventLog from './EventLog';

const Dashboard = () => {
  // Mock data - we'll replace this with real API calls later
  const [latestDistance, setLatestDistance] = useState(23);
  const [totalIncidents, setTotalIncidents] = useState(20);
  const [systemStatus, setSystemStatus] = useState('online');
  
  const [events, setEvents] = useState([
    { id: 200, sensorType: 'ultrasonic', distance: 23, timestamp: 'Jan 29, 2026 - 9:48:32 AM' },
    { id: 199, sensorType: 'ultrasonic', distance: 13, timestamp: 'Jan 29, 2026 - 9:48:29 AM' },
    { id: 198, sensorType: 'ultrasonic', distance: 13, timestamp: 'Jan 29, 2026 - 9:48:10 AM' },
    { id: 197, sensorType: 'ultrasonic', distance: 22, timestamp: 'Jan 29, 2026 - 9:03:56 AM' },
    { id: 196, sensorType: 'ultrasonic', distance: 28, timestamp: 'Jan 29, 2026 - 9:03:54 AM' },
    { id: 195, sensorType: 'ultrasonic', distance: 6, timestamp: 'Jan 29, 2026 - 9:03:48 AM' },
    { id: 194, sensorType: 'ultrasonic', distance: 5, timestamp: 'Jan 29, 2026 - 8:57:03 AM' },
  ]);

  return (
    <div className="min-h-screen bg-gray-100">
      {/* Header */}
      <header className="bg-white shadow-sm">
        <div className="max-w-7xl mx-auto px-4 sm:px-6 lg:px-8 py-4">
          <div className="flex items-center justify-between">
            <div className="flex items-center space-x-3">
              <div className="bg-blue-500 rounded-lg p-2">
                <svg className="w-6 h-6 text-white" fill="none" stroke="currentColor" viewBox="0 0 24 24">
                  <path strokeLinecap="round" strokeLinejoin="round" strokeWidth={2} d="M15 12a3 3 0 11-6 0 3 3 0 016 0z" />
                  <path strokeLinecap="round" strokeLinejoin="round" strokeWidth={2} d="M2.458 12C3.732 7.943 7.523 5 12 5c4.478 0 8.268 2.943 9.542 7-1.274 4.057-5.064 7-9.542 7-4.477 0-8.268-2.943-9.542-7z" />
                </svg>
              </div>
              <div>
                <h1 className="text-2xl font-bold text-gray-900">Silent Sentry Dashboard</h1>
                <p className="text-sm text-gray-500">Real-time Intruder Monitoring System</p>
              </div>
            </div>
            <div className="flex items-center space-x-2">
              <span className={`h-3 w-3 rounded-full ${systemStatus === 'online' ? 'bg-green-500' : 'bg-red-500'} animate-pulse`}></span>
              <span className="text-sm font-medium text-gray-700">
                System {systemStatus === 'online' ? 'Online' : 'Offline'}
              </span>
            </div>
          </div>
        </div>
      </header>

      {/* Main Content */}
      <main className="max-w-7xl mx-auto px-4 sm:px-6 lg:px-8 py-8">
        {/* Stats Cards */}
        <div className="grid grid-cols-1 md:grid-cols-2 gap-6 mb-8">
          <StatsCard 
            title="Latest Detection" 
            value={latestDistance} 
            unit="cm away"
            bgColor="bg-blue-50"
            textColor="text-blue-600"
            borderColor="border-blue-500"
          />
          <StatsCard 
            title="Total Incidents" 
            value={totalIncidents} 
            unit="logged (Recent)"
            bgColor="bg-red-50"
            textColor="text-red-600"
            borderColor="border-red-500"
          />
        </div>

        {/* Event Log */}
        <EventLog events={events} />
      </main>
    </div>
  );
};

export default Dashboard;